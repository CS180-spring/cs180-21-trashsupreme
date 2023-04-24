<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import DeleteButton from './DeleteButton.vue'
    export default defineComponent ({
        props: {
            item: Types.Item
        },
        components: {
            DeleteButton
        },
        emits: ['delete']
    })
</script>

<template>
    <div>
        📄Name: {{ item?.name }}, Size: {{ item?.size }}
        <DeleteButton @click="$emit('delete')" />
    </div>
</template>

<style>

</style>