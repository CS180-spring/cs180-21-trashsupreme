<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import AddButton from '../General_Components/AddButton.vue';
import DeleteButton from '../General_Components/DeleteButton.vue';
import { input } from '@/tailwindClasses';

    export default defineComponent ({
        data() {return {
            input,
            editing: false,
            currContent: this.content
        }},
        props: {
            content: String
        },
        components: {
            AddButton,
            DeleteButton
        },
        methods: {
            submit() {
                this.editing = false
                this.$emit('submit', this.currContent)
            }
        },
        emits: ['submit', 'addCell', 'deleteCell']
    })
</script>

<template>
    <span v-if="!editing" @click="editing = !editing" :style="{'border-color':'black', 'border-style':'solid'}">
        {{ currContent }} {{'\t'}}
    </span>
    <span v-if="editing">
        <input :class="input" v-model="currContent" @keyup.enter="submit"/>
        <AddButton @click="$emit('addCell')"/><DeleteButton @click="$emit('deleteCell')"/>
    </span>
</template>

<style>

</style>