<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import { sendUpdate } from '@/requests';
import DeleteButton from '../General_Components/DeleteButton.vue'
import TableView from './TableView.vue';
import EditableCell from './EditableCell.vue';
import TextCell from './TextCell.vue';

    export default defineComponent ({
        props: {
            item: Types.Item
        },
        data() {return {
            toggle: false,
            padding: (this.item != undefined) ? this.item.depth * 10 + "px" : "0px"
        }},
        components: {
            DeleteButton,
            TableView,
            TextCell
        },
        emits: ['delete'],
        methods: {
            uploadSubmit(content: string) {
                if (this.item != null) {
                    this.item.content = content
                    sendUpdate(this.item)
                }
            }
        }
    })
</script>

<template>
    <div :style="{'padding-left':padding}">
        <span @click="toggle = !toggle">
            📄Name: {{ item?.name }}, Extension: {{ item?.extension }}
        </span>
        <DeleteButton @click="$emit('delete')" />
    </div>
    <div v-if="toggle">
        <TableView v-if="item?.extension=='csv'" :content="item?.content" :delimiter="','" @submit="(content) => uploadSubmit(content)"/>
        <TableView v-if="item?.extension=='tsv'" :content="item?.content" :delimiter="'\t'" @submit="(content) => uploadSubmit(content)"/>
        <TextCell v-if="item?.extension=='txt' || item?.extension=='json'" :content="item?.content" @submit="(content) => {uploadSubmit(content)}"/>
    </div>
</template>

<style>

</style>